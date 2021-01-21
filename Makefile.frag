
INSTALL_DIR=$(shell pwd)/build/install

# download and build libcrypto.a for the CRT with -fPIC
build/deps/openssl:
	@echo Fetching libcrypto source
	git clone --depth=1 --single-branch --branch OpenSSL_1_1_1-stable https://github.com/openssl/openssl.git build/deps/openssl

$(INSTALL_DIR)/lib/libcrypto.a: build/deps/openssl
	@echo Building libcrypto
	cd build/deps/openssl && \
		./config -fPIC no-md2 no-rc5 no-rfc3779 no-sctp no-ssl-trace no-zlib no-hw no-mdc2 no-seed no-idea \
			no-camellia no-bf no-dsa no-ssl3 no-capieng \
			-DSSL_FORBID_ENULL -DOPENSSL_NO_DTLS1 -DOPENSSL_NO_HEARTBEATS \
			--prefix=$(INSTALL_DIR) --openssldir=$(INSTALL_DIR) && \
		make -j && \
		make install_sw


CMAKE_CONFIGURE = cmake -DCMAKE_INSTALL_PREFIX=$(INSTALL_DIR) -DCMAKE_PREFIX_PATH=$(INSTALL_DIR) -DBUILD_TESTING=OFF
CMAKE_BUILD = cmake --build
CMAKE_BUILD_TYPE ?= RelWithDebInfo
CMAKE_TARGET = --config $CMAKE_BUILD_TYPE --target install

# cmake configure depends on libcrypto above
build/aws-crt-ffi/CMakeCache.txt: $(INSTALL_DIR)/lib/libcrypto.a
	$(CMAKE_CONFIGURE) -Hcrt/aws-crt-ffi -Bbuild/aws-crt-ffi

# build the FFI library
$(INSTALL_DIR)/lib/libaws-crt-ffi.so: build/aws-crt-ffi/CMakeCache.txt
	$(CMAKE_BUILD) build/aws-crt-ffi $(CMAKE_TARGET)

# Force the crt object target to depend on the FFI library
src/crt.lo: $(INSTALL_DIR)/lib/libaws-crt-ffi.so
