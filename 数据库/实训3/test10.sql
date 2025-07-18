-- 10) 查询当前总的可用资产收益(被冻结的资产除外)前三名的客户的名称、身份证号及其总收益，按收益降序输出，总收益命名为total_income。不考虑并列排名情形。
--    请用一条SQL语句实现该查询：

-- output list
SELECT c_name, c_id_card, total_income
FROM client 
-- JOIN sub table TOTAL_INCOME _TABLE to get sum(pro_income)
JOIN (SELECT pro_c_id, sum(pro_income) as total_income FROM property
WHERE pro_status='可用'
GROUP BY pro_c_id
ORDER BY total_income DESC
limit 3)
total_income_table WHERE client.c_id=pro_c_id

/*  end  of  your code  */ 