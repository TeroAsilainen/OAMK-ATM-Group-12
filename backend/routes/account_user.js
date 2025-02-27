const express = require('express');
const router = express.Router();
const account_user = require('../models/account_user_model');

router.get('/', function(request, response){
    account_user.getAll(function(err, result){
        if(err){
            response.json(err);
        }    
        else {
            response.json(result);
        }
        
    })
});

router.get('/:iduser', function(request, response){
    account_user.getByIduser(request.params.iduser,function(err, result){
        if(err){
            response.send("-11");
        }    
        else {
            response.json(result);
        }
        
    })
});

router.post('/',function(request, response){
    account_user.add(request.body, function(err, result){
        if(err){
            response.json(err);
        }    
        else {
            response.json(result.affectedRows);
        }
    })
});

router.put('/:id',function(request, response){
    account_user.update(request.params.id,request.body, function(err, result){
        if(err){
            response.json(err);
        }    
        else {
            response.json(result.affectedRows);
        }
    })
});

router.delete('/:id',function(request, response){
    account_user.delete(request.params.id, function(err, result){
        if(err){
            response.json(err);
        }    
        else {
            response.json(result.affectedRows);
        }
    })
});

module.exports=router;