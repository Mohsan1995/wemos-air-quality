const config = require('./config.js')
const axios = require('axios')
const mqtt = require('mqtt')
const moment = require('moment')
const client = mqtt.connect(config.mqtt)

client.on('connect', function () {
  client.subscribe(config.topic["sub"])
})

client.on('message', function (topic, message) {
  console.log(message.toString())
  axios({
    method: 'post',
    url: config.backend,
    data: {
      air: message.toString(),
      date: moment().unix()
    }
  })
  .then(function(res){
    console.log(res.data);
  })
  .catch(function(e){
    console.log(e);
  });
})
