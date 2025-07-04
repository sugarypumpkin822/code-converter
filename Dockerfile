# Use official Qt base image
FROM qtproject/qt:5.15.2

WORKDIR /app
COPY . /app

RUN qmake CodeTranslator.pro && make -j$(nproc)

CMD ["./CodeTranslator"] 