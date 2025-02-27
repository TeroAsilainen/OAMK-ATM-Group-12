const db=require('../database');

const card_account={
    getAll:function(callback) {
        return db.query('SELECT * FROM card_account', callback);
    },
    getByIdcard:function(idcard, callback){
        return db.query('SELECT * FROM card_account WHERE idcard=?',[idcard], callback);
    },
    add:function(card_account_data, callback){
        return db.query('INSERT INTO card_account(idcard, idaccount) VALUES(?,?)',[card_account_data.idcard, card_account_data.idaccount], callback);
    },
    update:function(id, card_account_data, callback){
            return db.query('UPDATE card_account SET idcard=?, idaccount=? WHERE idcard_account=?', [card_account_data.idcard, card_account_data.idaccount, id], callback);
    },
    delete:function(id, callback){
        return db.query('DELETE FROM card_account WHERE idcard_account=?', [id], callback);
    }
}

module.exports=card_account;