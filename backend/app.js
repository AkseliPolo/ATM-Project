const express = require('express');
const PORT=3000;


const app=express();

app.use(express.json());

app.get('/',function(request,response){
    response.send("Esimerkki");
});

app.listen(PORT,function(){
    console.log("Palvelin kuuntelee porttia:"+PORT);
});

module.exports=app;