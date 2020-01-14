FROM ubuntu:18.04
LABEL maintainer="77676182@qq.com"
ENV REFRESHED_AT 2020-01-14

RUN apt-get -qq update && apt-get -qq install nginx

RUN mkdir -p /var/www/html/website
ADD nginx/global.conf /etc/nginx/conf.d/
ADD nginx/nginx.conf /etc/nginx/

EXPOSE 80
