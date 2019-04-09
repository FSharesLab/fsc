#!/bin/sh
cd /opt/fscio/bin

if [ ! -d "/opt/fscio/bin/data-dir" ]; then
    mkdir /opt/fscio/bin/data-dir
fi

if [ -f '/opt/fscio/bin/data-dir/config.ini' ]; then
    echo
  else
    cp /config.ini /opt/fscio/bin/data-dir
fi

if [ -d '/opt/fscio/bin/data-dir/contracts' ]; then
    echo
  else
    cp -r /contracts /opt/fscio/bin/data-dir
fi

while :; do
    case $1 in
        --config-dir=?*)
            CONFIG_DIR=${1#*=}
            ;;
        *)
            break
    esac
    shift
done

if [ ! "$CONFIG_DIR" ]; then
    CONFIG_DIR="--config-dir=/opt/fscio/bin/data-dir"
else
    CONFIG_DIR=""
fi

exec /opt/fscio/bin/nodfsc $CONFIG_DIR "$@"
