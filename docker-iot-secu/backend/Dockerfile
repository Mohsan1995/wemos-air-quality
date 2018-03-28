FROM php:7.1-apache

RUN apt-get update && \
    apt-get install -y \
        sendmail \
        libpng-dev \
        zlib1g-dev \
        openssl \
        git \
        pkg-config \
        libssl-dev \
        redis-server \
        libmcrypt-dev \
        libfreetype6-dev \
        libjpeg62-turbo-dev \
        libpng12-dev \
        libgd-dev


RUN docker-php-ext-configure gd --with-freetype-dir=/usr/include/ --with-jpeg-dir=/usr/include/ && \
        docker-php-ext-install \
            pdo mysqli \
            pdo pdo_mysql \
            mcrypt \
            mbstring \
            zip \
            gd \
            exif

# Install composer and put binary into $PATH
RUN curl -sS https://getcomposer.org/installer | php \
	&& mv composer.phar /usr/local/bin/ \
	&& ln -s /usr/local/bin/composer.phar /usr/local/bin/composer


# Install Phpunit
RUN curl -OL https://phar.phpunit.de/phpunit.phar \
	&& chmod 755 phpunit.phar \
	&& mv phpunit.phar /usr/local/bin/ \
	&& ln -s /usr/local/bin/phpunit.phar /usr/local/bin/phpunit

#Install node js
RUN curl -sL https://deb.nodesource.com/setup_8.x | bash - \
	&& apt-get install -y nodejs


# Install Gulp, Bower globally
RUN npm i -g gulp-cli bower
RUN npm install -g -s --no-progress yarn

RUN yarn global add @symfony/webpack-encore --dev
RUN yarn global add sass-loader node-sass --dev

RUN cd /tmp/ && \
    pecl install mongo mongodb

RUN echo "extension=mongodb.so" > $PHP_INI_DIR/conf.d/mongodb.ini


# Install XDebug, but not enable by default. Enable using:
# * php -d$XDEBUG_EXT vendor/bin/phpunit
# * php_xdebug vendor/bin/phpunit
RUN pecl install xdebug-2.5.0
ENV XDEBUG_EXT zend_extension=/usr/local/lib/php/extensions/no-debug-non-zts-20160303/xdebug.so
RUN alias php_xdebug="php -d$XDEBUG_EXT vendor/bin/phpunit"

RUN usermod -u 1000 www-data

RUN a2enmod rewrite
RUN a2enmod headers

# Clean
RUN apt-get clean
RUN rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* /var/cache/*
