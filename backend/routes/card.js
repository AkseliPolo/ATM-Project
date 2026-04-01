const express=require('express');
const card=require('../models/card_model');

const router=express.Router();

router.post('/',function(request,response){
    console.log(request.body);
    
    card.add(request.body, function(err, result){
        console.log("terve");
        if(err){
            
             return response.status(500).json({ error: err });

        }
        else{
            response.json(result);
        }
    });
});

module.exports=router;