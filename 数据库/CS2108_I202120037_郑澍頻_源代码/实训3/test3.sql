-- 3) 查询既买了保险又买了基金的客户的名称、邮箱和电话。结果依c_id排序
-- 请用一条SQL语句实现该查询：
SELECT client.c_name, client.c_mail, client.c_phone 
FROM client
WHERE c_id in (SELECT pro_c_id FROM property WHERE property.pro_type='2') AND c_id in (SELECT pro_c_id FROM property WHERE property.pro_type='3')
/*只有2/3 的时候可以， OR也可以 但加了AND就不能?*/
ORDER BY client.c_id;

/*  end  of  your code  */