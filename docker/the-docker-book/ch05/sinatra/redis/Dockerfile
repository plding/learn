FROM ubuntu:18.04
LABEL maintainer="77676182@qq.com"
ENV REFRESHED_AT 2020-01-14

RUN apt-get -qq update && apt-get -qq install redis-server redis-tools

EXPOSE 6379 

ENTRYPOINT ["/usr/bin/redis-server"]
CMD []
