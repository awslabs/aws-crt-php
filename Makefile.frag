
INSTALL_DIR=$(shell pwd)/build/install/

crt_libs=$(INSTALL_DIR)/lib/libaws-c-common.a \
	$(INSTALL_DIR)/lib/libaws-c-cal.a \
	$(INSTALL_DIR)/lib/libaws-c-io.a \
	$(INSTALL_DIR)/lib/libaws-c-compression.a \
	$(INSTALL_DIR)/lib/libaws-c-http.a \
	$(INSTALL_DIR)/lib/libaws-c-auth.a \
	$(INSTALL_DIR)/lib/libs2n.a

crt-static: $(crt_libs) $(INSTALL_DIR)/lib/libcrypto.a

build/deps/openssl:
	@echo Fetching libcrypto source
	git clone --single-branch --branch OpenSSL_1_1_1 https://github.com/openssl/openssl.git build/deps/openssl

$(INSTALL_DIR)/lib/libcrypto.a: build/deps/openssl
	@echo Building libcrypto
	cd build/deps/openssl && \
		./config -fPIC no-md2 no-rc5 no-rfc3779 no-sctp no-ssl-trace no-zlib no-hw no-mdc2 no-seed no-idea \
			no-camellia no-bf no-dsa no-ssl3 no-capieng \
			-DSSL_FORBID_ENULL -DOPENSSL_NO_DTLS1 -DOPENSSL_NO_HEARTBEATS \
			--prefix=$(INSTALL_DIR) --openssldir=$(INSTALL_DIR) && \
		make -j && \
		make install_sw


CMAKE_CONFIGURE = cmake -DCMAKE_INSTALL_PREFIX=$(shell pwd)/build/install -DCMAKE_PREFIX_PATH=$(shell pwd)/build/install CMAKE_INSTALL_LIBDIR=$(shell pwd)/build/install/lib -DBUILD_TESTING=OFF -DLibCrypto_INCLUDE_DIR=$(INSTALL_DIR)/include -DLibCrypto_STATIC_LIBRARY=$(INSTALL_DIR)/lib/libcrypto.a
CMAKE_BUILD = cmake --build
CMAKE_BUILD_TYPE ?= RelWithDebInfo
CMAKE_TARGET = --config $CMAKE_BUILD_TYPE --target install

build/aws-c-common/CMakeCache.txt: $(INSTALL_DIR)/lib/libcrypto.a
	$(CMAKE_CONFIGURE) -Hcrt/aws-c-common -Bbuild/aws-c-common

$(INSTALL_DIR)/lib/libaws-c-common.a: build/aws-c-common/CMakeCache.txt
	$(CMAKE_BUILD) build/aws-c-common $(CMAKE_TARGET)

build/s2n/CMakeCache.txt: $(INSTALL_DIR)/lib/libcrypto.a
	$(CMAKE_CONFIGURE) -Hcrt/s2n -Bbuild/s2n

$(INSTALL_DIR)/lib/libs2n.a: build/s2n/CMakeCache.txt
	$(CMAKE_BUILD) build/s2n $(CMAKE_TARGET)

build/aws-c-io/CMakeCache.txt: $(INSTALL_DIR)/lib/libaws-c-common.a $(INSTALL_DIR)/lib/libcrypto.a $(INSTALL_DIR)/lib/libs2n.a
	$(CMAKE_CONFIGURE) -Hcrt/aws-c-io -Bbuild/aws-c-io

$(INSTALL_DIR)/lib/libaws-c-io.a: build/aws-c-io/CMakeCache.txt
	$(CMAKE_BUILD) build/aws-c-io $(CMAKE_TARGET)

build/aws-c-cal/CMakeCache.txt: $(INSTALL_DIR)/lib/libaws-c-common.a
	$(CMAKE_CONFIGURE) -Hcrt/aws-c-cal -Bbuild/aws-c-cal

$(INSTALL_DIR)/lib/libaws-c-cal.a: build/aws-c-cal/CMakeCache.txt
	$(CMAKE_BUILD) build/aws-c-cal $(CMAKE_TARGET)

build/aws-c-compression/CMakeCache.txt: $(INSTALL_DIR)/lib/libaws-c-common.a
	$(CMAKE_CONFIGURE) -Hcrt/aws-c-compression -Bbuild/aws-c-compression

$(INSTALL_DIR)/lib/libaws-c-compression.a: build/aws-c-compression/CMakeCache.txt
	$(CMAKE_BUILD) build/aws-c-compression $(CMAKE_TARGET)

build/aws-c-http/CMakeCache.txt: $(INSTALL_DIR)/lib/libaws-c-compression.a $(INSTALL_DIR)/lib/libaws-c-io.a
	$(CMAKE_CONFIGURE) -Hcrt/aws-c-http -Bbuild/aws-c-http

$(INSTALL_DIR)/lib/libaws-c-http.a: build/aws-c-http/CMakeCache.txt
	$(CMAKE_BUILD) build/aws-c-http $(CMAKE_TARGET)

build/aws-c-auth/CMakeCache.txt: $(INSTALL_DIR)/lib/libaws-c-http.a
	$(CMAKE_CONFIGURE) -Hcrt/aws-c-auth -Bbuild/aws-c-auth

$(INSTALL_DIR)/lib/libaws-c-auth.a: build/aws-c-auth/CMakeCache.txt
	$(CMAKE_BUILD) build/aws-c-auth $(CMAKE_TARGET)

src/crt.lo: crt-static
