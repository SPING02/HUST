# 请填写语句，完成以下功能：
# (1) 创建角色client_manager和fund_manager；
CREATE ROLE client_manager, fund_manager;

# (2) 授予client_manager对client表拥有select,insert,update的权限；
GRANT SELECT, INSERT, UPDATE
ON TABLE client 
TO client_manager;

# (3) 授予client_manager对bank_card表拥有查询除银行卡余额外的select权限；
GRANT SELECT (b_number, b_c_id, b_type)
ON TABLE bank_card
TO client_manager;

# (4) 授予fund_manager对fund表的select,insert,update权限；
GRANT SELECT, INSERT, UPDATE
ON TABLE fund
TO fund_manager;

# (5) 将client_manager的权限授予用户tom和jerry；
GRANT client_manager
TO tom, jerry;

# (6) 将fund_manager权限授予用户Cindy.
GRANT fund_manager
TO Cindy;