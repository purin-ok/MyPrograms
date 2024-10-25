# Tomcatイメージをダウンロード
FROM tomcat:10.1.0-jdk17

# 下記補足にて
RUN rm -r /usr/local/tomcat/webapps
RUN mv /usr/local/tomcat/webapps.dist /usr/local/tomcat/webapps

# ローカルのソースコードのマウントするディレクトリを作成
RUN mkdir /usr/local/tomcat/webapps/hoge
