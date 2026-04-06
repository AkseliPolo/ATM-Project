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

router.get('/',function(request, response){
    card.getAllCards(function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});

router.delete('/:id',function(request, response){
    card.deleteCard(request.params.id, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});

module.exports=router;