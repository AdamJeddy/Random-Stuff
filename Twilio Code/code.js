const express = require('express');
const app = express();
const bodyparser = require('body-parser');

app.use(bodyparser.urlencoded({extended:true}));

app.get('/', (request, response) =>{
    
const twilio = require('twilio')('ACCOUNTSID','AUTHTOKEN');

twilio.studio.flows('FLOWSID')
             .executions
             .create({to: 'PHONENUM', from: 'TWILLIOPHONENUM'})
             .then(execution => console.log(execution.sid))
             .catch(error => console.log(error))

response.sendStatus(200)
});

app.listen(3000, ()=> {console.log('Server Running...')});