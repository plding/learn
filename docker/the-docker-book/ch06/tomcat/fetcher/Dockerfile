FROM registry.cn-beijing.aliyuncs.com/base-1d1d100/ubuntu:16.04-190828
LABEL maintainer="77676182@qq.com"
ENV REFRESHED_AT 2020-01-14

RUN apt-get -qq update
RUN apt-get -qq install wget

VOLUME ["/var/lib/tomcat8/webapps/"]
WORKDIR /var/lib/tomcat8/webapps/

ENTRYPOINT ["wget"]
CMD ["--help"]
