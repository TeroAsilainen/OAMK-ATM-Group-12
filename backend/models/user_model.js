const db = require('../database');

const user = {
    getAll:function(callback) {
        return db.query('SELECT * FROM user', callback);
    },
    getById:function(id, callback){
        return db.query('SELECT * FROM user WHERE iduser=?', [id], callback);
    },
    add:function(user_data, callback){
        return db.query(
            'INSERT INTO user (fname, lname, phonenumber, address) VALUES (?,?,?,?)' 
            [user_data.fname, user_data.lname, user_data.phonenumber, user_data.address], callback);

    },
    update:function(id, user_data, callback){
        return db.query(
            'UPDATE user SET fname=?, lname=?, phonenumber=?, address=? WHERE iduser=?'
        [user_data.fname, user_data.lname, user_data.phonenumber, user_data.address], callback);
    },
    delete:function(id, callback){
        return db.query(
            'DELETE FROM user WHERE iduser=?',
        );
    }

}

module.exports=user;