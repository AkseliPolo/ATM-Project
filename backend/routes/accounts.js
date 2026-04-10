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

router.get('/balance/:id',function(request, response){
    accounts.getBalanceWithCardNum(request.params.id, function(err, result){
        if(err){
            response.send(err);
        }
        else{
             response.json(result[0].balance); 
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