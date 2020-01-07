package com.plding.learnkafka.ch03;

import org.apache.kafka.clients.producer.KafkaProducer;
import org.apache.kafka.clients.producer.RecordMetadata;
import org.apache.kafka.clients.producer.Producer;
import org.apache.kafka.clients.producer.ProducerRecord;

import java.util.Properties;
import java.util.concurrent.Future;

public class AvroProducer {
    public static void main(String[] args) {
        Properties p = new Properties();

        p.put("bootstrap.servers", "kafka:9092");
        p.put("key.serializer", "org.apache.kafka.common.serialization.StringSerializer");
        p.put("value.serializer", "io.confluent.kafka.serializers.KafkaAvroSerializer");
        p.put("schema.registry.url", "http://kafka:8081");

        Producer<String, User> pd = new KafkaProducer<>(p);

        User user = UserGenerator.getNext();
        ProducerRecord<String, User> rec = new ProducerRecord<>("avrotopic", user.getName().toString(), user);
        try {
            Future<RecordMetadata> resultFuture = pd.send(rec);
            System.out.println("Avro Message sent to partition " + resultFuture.get().partition());
            System.out.println("Offset of the message is " + resultFuture.get().offset());
            System.out.println("Topic of the message is " + resultFuture.get().topic());
        } catch (Exception e) {
            System.out.println("Failed to send Avro message");
            e.printStackTrace();
        }
    }
}
