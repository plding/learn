FROM ubuntu:18.04
LABEL maintainer="77676182@qq.com"
ENV REFRESHED_AT 2020-01-14

RUN apt-get -qq update
RUN apt-get -qq install nodejs npm
RUN ln -s /usr/bin/nodejs /usr/bin/node
RUN mkdir -p /var/log/nodeapp

ADD nodeapp /opt/nodeapp/

WORKDIR /opt/nodeapp
RUN npm install

VOLUME ["/var/log/nodeapp"]

EXPOSE 3000

ENTRYPOINT ["nodejs", "server.js"]
