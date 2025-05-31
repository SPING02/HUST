-- 4) 查询办理了储蓄卡的客户名称、手机号、银行卡号。 查询结果结果依客户编号排序。
--    请用一条SQL语句实现该查询：
SELECT client.c_name, client.c_phone, bank_card.b_number
FROM client INNER JOIN bank_card ON bank_card.b_c_id=client.c_id
WHERE bank_card.b_type='储蓄卡'
GROUP BY bank_card.b_number
ORDER BY client.c_id;



/*  end  of  your code  */