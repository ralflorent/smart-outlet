# set base image
FROM nginx:1.16.0-alpine

# default tcp port for container
EXPOSE 80

# declare env variables
ENV APP_DIR /usr/share/nginx/html
ENV CONF_DIR /etc/nginx/conf.d/

# change working directory
WORKDIR $APP_DIR

# delete existing html content from nginx server
RUN rm -r *

# copy new html content to nginx server
COPY dist/smart-outlet .

# override nginx server default config
WORKDIR $CONF_DIR
RUN mv default.conf default.conf.bak
COPY nginx.conf ./default.conf

# launch nginx
CMD ["nginx", "-g", "daemon off;"]