# FSCIO Kafka Plugin
## what's fscio kafka plugin
FSCIO Kafka Plugin is used to receive the transaction data fom blockchain and send out the transaction through kafka producer. Developer can receive the transaction data through kafka consumer in the background application.

## how does the kafka plugin work

1. it run a task to resume the transactions on chain. there's two type of transactions:"applied transaction" and "accepted transaction"

2. create two kafka topics, the producer of which store the applied transaction and accepted transaction in kafka queue

3. the dapp developer can get the transaction data through the consumer of the kafka topic.

## Based fscio version
fsc.io-1.6.1 or later

## Building the plugin [Install on your nodfsc server]

1. install kafka library
```
cd /usr/local
git clone https://github.com/edenhill/librdkafka.git
cd librdkafka
./configure
make
sudo make install
```
2. download the kafka plugin code in to fsc file
```
cd /usr/local/fsc/plugins/
git clone https://github.com/tokenbankteam/kafka_plugin.git
```
3. update the CMakeLists.txt to complie the kafka plugin 
```
(1)edit /usr/local/fsc/plugins/CMakeLists.txt:
add_subdirectory(kafka_plugin)

(2)edit /usr/local/fsc/programs/nodfsc/CMakeLists.txt:
target_link_libraries( nodfsc PRIVATE -Wl,${whole_archive_flag} kafka_plugin -Wl,${no_whole_archive_flag} )
```

## How to setup on your nodfsc
Enable this plugin using --plugin option to nodfsc or in your config.ini. Use nodfsc --help to see options used by this plugin.

## Configuration
Add the following to config.ini to enable the plugin:
```
parmeters for kafka_plugin
 --plugin fscio::kafka_plugin     //add kafka plugin
 --kafka-uri 192.168.31.225:9092    //the kafka service 
 --accept_trx_topic fsc_accept_topic //the kafka topic for accept transaction
 --applied_trx_topic fsc_applied_topic //the applied topic for applied transaction
 --kafka-block-start 100  //the start block number, from which kafka begin to receive transactions
 --kafka-queue-size 5000  // the queue size of kafka
```
