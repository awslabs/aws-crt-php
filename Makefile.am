
libcrypto_path := $(shell pwd)/build/deps/openssl/install

${libcrypto_path}/lib/libcrypto.a:
    mkdir -p build/deps/openssl 2>&1 > /dev/null
    git clone --single-branch --branch OpenSSL_1_1_1 https://github.com/openssl/openssl.git build/deps/openssl
    pushd build/deps/openssl
    ./config -fPIC no-md2 no-rc5 no-rfc3779 no-sctp no-ssl-trace no-zlib no-hw no-mdc2 no-seed no-idea no-camellia no-bf no-dsa no-ssl3 no-capieng -DSSL_FORBID_ENULL -DOPENSSL_NO_DTLS1 -DOPENSSL_NO_HEARTBEATS --prefix=${libcrypto_path} --openssldir=${libcrypto_path}
    make -j
    make install_sw
    popd

build/CMakeCache.txt:
    cmake -H. -Bbuild -DCMAKE_INSTALL_PREFIX=build/lib -DLibCrypto_INCLUDE_DIR=${libcrypto_path}/include -DLibCrypto_STATIC_LIBRARY=${libcrypto_path}/lib/libcrypto.a

build/lib/libaws-c-%.a build/lib/s2n.a: build/CMakeCache.txt
    cmake --build build --target install

clean:
    git clean -xfd
