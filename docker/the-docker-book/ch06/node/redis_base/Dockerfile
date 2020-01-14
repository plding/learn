FROM registry.cn-beijing.aliyuncs.com/base-1d1d100/ubuntu:16.04-190828
LABEL maintainer="77676182@qq.com"
ENV REFRESHED_AT 2020-01-14

RUN apt-get -qq update
RUN apt-get -qq install software-properties-common
RUN add-apt-repository ppa:chris-lea/redis-server
RUN apt-get -qq update
RUN apt-get -qq install redis-server redis-tools

VOLUME ["/var/lib/redis", "/var/log/redis"]

EXPOSE 6379

CMD []
