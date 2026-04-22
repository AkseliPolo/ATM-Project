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
 
router.get('/getCardLock/:cardNum',function(request, response){
    card.getCardLock(request.params.cardNum, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.send(String(result[0].card_locked));
        }
    });
});
 
router.get('/getCardLockTime/:cardNum',function(request, response){
    card.getCardLockTime(request.params.cardNum, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.send(result[0].locked_time);
        }
    });
});
router.patch('/:cardNum/lock',function(request, response){
    card.lockCard(request.params.cardNum,function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});
 
router.patch('/:cardNum/removelock',function(request, response){
    card.removeLockCard(request.params.cardNum,function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});

router.get('/getCardType/:cardNum',function(request, response){
    card.getCardTypeWithCardNum(request.params.cardNum, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.send(String(result[0].card_type));
        }
    });
});
 
module.exports=router;
 