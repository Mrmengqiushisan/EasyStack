--create table t_user
CREATE TABLE IF NOT EXISTS t_user(
    f_id            bigint(20) NOT NULL AUTO_INCREMENT COMMENT '自增ID',
    f_user_id       bigint(20) NOT NULL COMMENT '用户ID',
    f_username      varchar(64) NOT NULL COMMENT '用户名',
    f_nickname      varchar(64) NOT NULL COMMENT '用户昵称',
    f_password      varchar(64) NOT NULL COMMENT '用户密码',
    f_facetype      int(10) DEFAULT 0 COMMENT '用户头像类型',
    f_customface    varchar(32) DEFAULT NULL COMMENT '自定义头像名',
    f_customfacefmt varchar(6) DEFAULT NULL COMMENT '自定义头像格式',
    f_gender        int(2) DEFAULT 0 COMMENT '性别',
    f_birthday      bigint(20)  DEFAULT 19900101 COMMENT '生日',
    f_signature     varchar(256) DEFAULT NULL COMMENT '地址',
    f_address       varchar(256) DEFAULT NULL COMMENT '地址',
    f_phonenumber   varchar(64) DEFAULT NULL COMMENT '电话',
    f_mail          varchar(256) DEFAULT NULL COMMENT '邮箱',
    f_owner_id      bigint(20) DEFAULT 0 COMMENT '群账号群主userid',
    f_register_time datetime NOT NULL COMMENT '注册时间',
    f_remark        varchar(64) NULL COMMENT '备注',
    f_update_time   timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间',
    PRIMARY KEY (f_user_id), INDEX f_user_id (f_user_id), KEY  f_id  ( f_id )
) default charset=utf8mb4,ENGINE=InnoDB;
--create table t_chatmsg
CREATE TABLE IF NOT EXISTS t_chatmsg(
    f_id            bigint(20) NOT NULL AUTO_INCREMENT COMMENT '自增ID',
    f_senderid      bigint(20) NOT NULL COMMENT '发送者id',
    f_targetid      bigint(20) NOT NULL COMMENT '接收者id',
    f_msgcontent    blob NOT NULL COMMENT '聊天内容',
    f_create_time   timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间',
    f_remark        varchar(64) NULL COMMENT '备注',
    PRIMARY KEY (f_id), INDEX f_id (f_id)
)default charset=utf8mb4,ENGINE=InnoDB;
--create table t_user_relationship
CREATE TABLE IF NOT EXISTS t_user_relationship(
    f_id bigint(20) NOT NULL AUTO_INCREMENT COMMENT '自增ID',
    f_user_id1 bigint(20) NOT NULL COMMENT '用户ID',
    f_user_id2 bigint(20) NOT NULL COMMENT '用户ID',
    f_remark varchar(64) NULL COMMENT '备注',
    f_create_time timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间',
    PRIMARY KEY (f_id), INDEX f_id (f_id)
)default charset=utf8mb4,ENGINE=InnoDB;