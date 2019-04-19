ARG baseEnvDeocker=fscio/builder

FROM $baseEnvDeocker as builder

ARG branch=master
ARG symbol=FSC
ARG precision=8

RUN git clone -b $branch https://github.com/FutureSharesCloud/fsc.git --recursive \
    && cd fsc && echo "$branch:$(git rev-parse HEAD)" > /etc/fscio-version \
    && cmake -H. -B"/tmp/build" -GNinja -DCMAKE_BUILD_TYPE=Release -DWASM_ROOT=/opt/wasm -DCMAKE_CXX_COMPILER=clang++ \
       -DCMAKE_C_COMPILER=clang -DCMAKE_INSTALL_PREFIX=/tmp/build -DBUILD_MONGO_DB_PLUGIN=true -DBUILD_KAFKA_PLUGIN=true -DCORE_SYMBOL_NAME=$symbol -DCORE_SYMBOL_PRECISION=$precision \
    && cmake --build /tmp/build --target install


FROM ubuntu:18.04

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get -y install openssl ca-certificates && rm -rf /var/lib/apt/lists/*
COPY --from=builder /usr/local/lib/* /usr/local/lib/
COPY --from=builder /tmp/build/bin /opt/fscio/bin
COPY --from=builder /tmp/build/contracts /contracts
COPY --from=builder /fsc/Docker/config.ini /
COPY --from=builder /etc/fscio-version /etc
COPY --from=builder /etc/ld.so.conf.d/rdkafka.conf /etc/ld.so.conf.d/
COPY --from=builder /fsc/Docker/nodfscd.sh /opt/fscio/bin/nodfscd.sh
ENV FSCIO_ROOT=/opt/fscio
RUN chmod +x /opt/fscio/bin/nodfscd.sh
ENV LD_LIBRARY_PATH /usr/local/lib
ENV PATH /opt/fscio/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
