const express = require('express');
const router = express.Router();
const account = require('../models/account_model');

router.get('/', function(request, response){
    account.getAll(function(err, result){
        if(err){
            response.json(err);
        }
        else {
            response.json(result);

        }
    })
});

router.get('/:id', function(request, response){
    account.getById(request.params.id, function(err, result){
        if(err){
            response.send("-11");
        }
        else {
            response.json(result[0]);

        }
    })
});

router.post('/', function(request, response){
    account.add(request.body, function(err, result){
        if(err){
            response.json(err);
        }
        else {
            response.json(result.affectedRows);
        }
    })
});

router.put('/:id', function(request, response){
    account.update(request.params.id, request.body, function(err, result){
        if(err){
            response.json(err);
        }
        else {
            response.json(result.affectedRows);
        }
    })
});

router.delete('/:id', function(request, response){
    account.delete(request.params.id, function(err, result){
        if(err){
        response.json(err);
        }
        else {
        response.json(result.affectedRows);
        }
    })
});

module.exports = router;