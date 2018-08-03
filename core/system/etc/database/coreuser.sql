PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE coreuser(
id int auto_inrement not null primary key,
accDesc text not null,
user varchar(40) not null,
password varchar(40) not null,
inuse bit default 1 not null);
INSERT INTO coreuser VALUES(0,'text-account','admin','<Core-Admin-2018-Sqlite>',1);
COMMIT;
