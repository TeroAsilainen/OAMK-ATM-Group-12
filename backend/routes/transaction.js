const express = require('express');
const router = express.Router();
const transaction = require('../models/transaction_model');

router.get('/', function(request, response){
    transaction.getAll(function(err, result){
        if(err){
            response.json(err);
        }    
        else {
            response.json(result);
        }
        
    })
});

router.post('/:idaccount', function(request, response){
    transaction.getByIdaccount(request.params.idaccount, request.body, function(err, result){
        if(err){
            response.send("-11");
        }    
        else {
            response.json(result);
        }
        
    })
});

router.post('/',function(request, response){
    transaction.add(request.body, function(err, result){
        if(err){
            response.json(err);
        }    
        else {
            response.json(result.affectedRows);
        }
    })
});

router.put('/:id',function(request, response){
    transaction.update(request.params.id,request.body, function(err, result){
        if(err){
            response.json(err);
        }    
        else {
            response.json(result.affectedRows);
        }
    })
});

router.delete('/:id',function(request, response){
    transaction.delete(request.params.id, function(err, result){
        if(err){
            response.json(err);
        }    
        else {
            response.json(result.affectedRows);
        }
    })
});

module.exports=router;