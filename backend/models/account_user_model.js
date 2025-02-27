const db=require('../database');

const account_user={
    getAll:function(callback) {
        return db.query('SELECT * FROM account_user', callback);
    },
    getByIduser:function(iduser, callback){
        return db.query('SELECT * FROM account_user WHERE iduser=?',[iduser],callback);
    },
    add:function(account_user_data, callback){
        return db.query('INSERT INTO account_user(idaccount, iduser, idowner) VALUES(?,?,?)',[account_user_data.idaccount, account_user_data.iduser, account_user_data.idowner], callback);
    },
    update:function(id,account_user_data, callback){
        return db.query('UPDATE account_user SET idaccount=?, iduser=?, idowner=? WHERE idaccount_user=?',[account_user_data.idaccount, account_user_data.iduser, account_user_data.idowner, id], callback);
    },
    delete:function(id, callback){
        return db.query('DELETE FROM account_user WHERE idaccount_user=?', [id], callback);
    }
}

module.exports=account_user;