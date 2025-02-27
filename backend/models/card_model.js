const db=require('../database');
const bcrypt=require('bcryptjs');

const card={
    getAll:function(callback) {
        return db.query('SELECT * FROM card', callback);
    },
    getById:function(id, callback){
        return db.query('SELECT * FROM card WHERE idcard=?', [id], callback);
    },
    add:function(card_data, callback){
        bcrypt.hash(card_data.pin, 10, function(err, hash) {
            return db.query('INSERT INTO card (idcard, pin, cardtype, wrong_attempts, iduser) VALUES(?,?,?,?,?)', [card_data.idcard, hash, card_data.cardtype, card_data.wrong_attempts, card_data.iduser], callback);
          })
    },
    update:function(id, card_data, callback){
        bcrypt.hash(card_data.pin, 10, function(err, hash){
            return db.query('UPDATE card SET pin=?, cardtype=?, wrong_attempts=?, iduser=? WHERE idcard=?', [hash, card_data.cardtype, card_data.wrong_attempts, card_data.iduser, id], callback);
        })
    },
    delete:function(id, callback){
        return db.query('DELETE FROM card WHERE idcard=?', [id], callback);
    },
    checkPin:function(username, callback){
        return db.query('SELECT pin FROM card WHERE idcard=?', [username], callback);
    },
    getWrongAttemptsById:function(idcard, callback){
        return db.query('SELECT wrong_attempts FROM card WHERE idcard=?', [idcard], callback);
    },
    updateWrongAttempts:function(idcard, card_data, callback){
        return db.query('UPDATE card SET wrong_attempts=? WHERE idcard=?',[ card_data.wrong_attempts, idcard], callback);
    }
}

module.exports=card;