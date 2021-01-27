
BUILD_DIR=$(shell pwd)/build
DEPS_DIR=$(BUILD_DIR)/deps
INT_DIR=$(BUILD_DIR)/install
INSTALL_DIR=$(shell pwd)

# download and build libcrypto.a for the CRT with -fPIC
$(DEPS_DIR)/openssl:
	@echo Fetching libcrypto source
	git clone --depth=1 --single-branch --branch OpenSSL_1_1_1-stable https://github.com/openssl/openssl.git $(DEPS_DIR)/openssl

$(INT_DIR)/lib/libcrypto.a: $(DEPS_DIR)/openssl
	@echo Building libcrypto
	cd $(DEPS_DIR)/openssl && \
		./config -fPIC no-md2 no-rc5 no-rfc3779 no-sctp no-ssl-trace no-zlib no-hw no-mdc2 no-seed no-idea \
			no-camellia no-bf no-dsa no-ssl3 no-capieng \
			-DSSL_FORBID_ENULL -DOPENSSL_NO_DTLS1 -DOPENSSL_NO_HEARTBEATS \
			--prefix=$(INT_DIR) --openssldir=$(INT_DIR) && \
		make -j && \
		make install_sw


CMAKE_CONFIGURE = cmake -DCMAKE_INSTALL_PREFIX=$(INT_DIR) -DCMAKE_PREFIX_PATH=$(INT_DIR) -DLibCrypto_INCLUDE_DIR=$(INT_DIR)/include -DLibCrypto_STATIC_LIBRARY=$(INT_DIR)/lib/libcrypto.a -DBUILD_TESTING=OFF
CMAKE_BUILD = cmake --build
CMAKE_BUILD_TYPE ?= RelWithDebInfo
CMAKE_TARGET = --config $(CMAKE_BUILD_TYPE) --target install

# cmake configure depends on libcrypto above
$(BUILD_DIR)/aws-crt-ffi/CMakeCache.txt: $(INT_DIR)/lib/libcrypto.a
	$(CMAKE_CONFIGURE) -Hcrt/aws-crt-ffi -Bbuild/aws-crt-ffi

# build the FFI library
$(BUILD_DIR)/aws-crt-ffi/libaws-crt-ffi.so: $(BUILD_DIR)/aws-crt-ffi/CMakeCache.txt
	$(CMAKE_BUILD) build/aws-crt-ffi $(CMAKE_TARGET)

# copy the lib into the lib folder
$(INSTALL_DIR)/lib/libaws-crt-ffi.so: $(BUILD_DIR)/aws-crt-ffi/libaws-crt-ffi.so
	cp -v $(BUILD_DIR)/aws-crt-ffi/libaws-crt-ffi.so $(INSTALL_DIR)/lib/libaws-crt-ffi.so

# Force the crt object target to depend on the FFI library
src/crt.lo: $(INSTALL_DIR)/lib/libaws-crt-ffi.so
