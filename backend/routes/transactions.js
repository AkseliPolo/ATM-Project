const express=require('express');
const transactions=require('../models/transactions_model');

const router=express.Router();

router.post('/', function(request, response){
    transactions.add(request.body, function(err, result){
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
    transactions.getAllTransactions(function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});

router.get('/:id',function(request, response){
    transactions.getTransactionWithId(request.params.id, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});

router.get('/account/:id',function(request, response){
    transactions.getTransactionWithAccountId(request.params.id, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});
router.put('/:id',function(request, response){
    transactions.updateTransactionWithId(request.params.id, request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});

router.delete('/:id',function(request, response){
    transactions.deleteTransactionWithId(request.params.id, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});

module.exports=router;