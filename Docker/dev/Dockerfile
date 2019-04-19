FROM fscio/builder
ARG branch=master
ARG symbol=FSC
ARG precision=8

RUN git clone -b $branch https://github.com/FutureSharesCloud/fsc.git --recursive \
    && cd fsc && echo "$branch:$(git rev-parse HEAD)" > /etc/fscio-version \
    && cmake -H. -B"/opt/fscio" -GNinja -DCMAKE_BUILD_TYPE=Release -DWASM_ROOT=/opt/wasm -DCMAKE_CXX_COMPILER=clang++ \
       -DCMAKE_C_COMPILER=clang -DCMAKE_INSTALL_PREFIX=/opt/fscio -DBUILD_MONGO_DB_PLUGIN=true -DCORE_SYMBOL_NAME=$symbol -DCORE_SYMBOL_PRECISION=$precision  \
    && cmake --build /opt/fscio --target install \
    && cp /fsc/Docker/config.ini / && ln -s /opt/fscio/contracts /contracts && cp /fsc/Docker/nodfscd.sh /opt/fscio/bin/nodfscd.sh && ln -s /fsc/tutorials /tutorials

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get -y install openssl ca-certificates vim psmisc python3-pip && rm -rf /var/lib/apt/lists/*
RUN pip3 install numpy
ENV FSCIO_ROOT=/opt/fscio
RUN chmod +x /opt/fscio/bin/nodfscd.sh
ENV LD_LIBRARY_PATH /usr/local/lib
ENV PATH /opt/fscio/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
