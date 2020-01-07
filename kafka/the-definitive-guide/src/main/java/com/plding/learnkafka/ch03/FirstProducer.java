package com.plding.learnkafka.ch03;

import org.apache.kafka.clients.producer.KafkaProducer;
import org.apache.kafka.clients.producer.Producer;
import org.apache.kafka.clients.producer.ProducerRecord;

import java.util.Properties;
import java.util.concurrent.ExecutionException;

public class FirstProducer {
    public static void main(String[] args) {
        Properties p = new Properties();

        // Declare the properties of cluster and information about data key and value
        p.put("bootstrap.servers", "kafka:9092");
        p.put("key.serializer", "org.apache.kafka.common.serialization.StringSerializer");
        p.put("value.serializer", "org.apache.kafka.common.serialization.StringSerializer");

        // Create producer and send data in format: (topic name, key, value)
        Producer<String, String> pd = new KafkaProducer<>(p);
        ProducerRecord<String, String> rec = new ProducerRecord<>("firsttopic", "key", "value");

        // Kafka has 3 methods of sending
        // 1) Fire and forget
        pd.send(rec);

        // 2) Syncronous send, wait for response object
        try {
            pd.send(rec).get();
        } catch (InterruptedException | ExecutionException e) {
            e.printStackTrace();
        }

        // 3) Asynchronous send, given a call back function and track success using callback
        pd.send(rec, new MyCallback());

        pd.close();
    }
}
