const express=require('express');
const accounts=require('../models/accounts_model');
 
const router=express.Router();
 
router.post('/', function(request, response){
    accounts.add(request.body, function(err, result){
        if(err)
        {
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});
 
router.get('/',function(request, response){
    accounts.getAllAccounts(function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});
 
router.get('/:id',function(request, response){
    accounts.getAccountWithId(request.params.id, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});
 
router.get('/card/:cardNumber', function(request, response) {
    accounts.getAccountByCardNumber(request.params.cardNumber, function(err, result) {
        if (err) {
            response.send(err);
        } else {
            response.send(String(result[0].idAccount));
        }
    });
});
 
router.get('/balanceId/:id',function(request, response){
    accounts.getBalanceWithId(request.params.id, function(err, result){
        if(err){
            response.send(err);
        }
        else{
             response.json(result[0].balance);
        }
    });
});
 
 
router.get('/balance/:card',function(request, response){
    accounts.getBalanceWithCardNum(request.params.card, function(err, result){
        if(err){
            response.send(err);
        }
        else{
             response.json(result[0].balance);
        }
    });
});
 
router.get('/credit_used/:card',function(request, response){
    accounts.getCredit_UsedWithCardNum(request.params.card, function(err, result){
        if(err){
            response.send(err);
        }
        else{
             response.send((result[0].credit_used));
        }
    });
});
 
router.get('/credit_limit/:card',function(request, response){
    accounts.getCredit_LimitWithCardNum(request.params.card, function(err, result){
        if(err){
            response.send(err);
        }
        else{
             response.send((result[0].credit_limit));
        }
    });
});
 
router.get('/card_type/:card',function(request, response){
    accounts.getCard_TypeWithCardNum(request.params.card, function(err, result){
        if(err){
            response.send(err);
        }
        else{
             response.send((result[0].card_type));
        }
    });
});
 
 
router.get('/customer/:customerId',function(request, response){
    accounts.getAccountWithCustomerId(request.params.customerId, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});
 
 
 
router.put('/:id',function(request, response){
    accounts.updateAccountWithId(request.params.id, request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});
 
router.delete('/:id',function(request, response){
    accounts.deleteAccountWithId(request.params.id, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});
 
module.exports=router;