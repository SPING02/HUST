-- 13) 综合客户表(client)、资产表(property)、理财产品表(finances_product)、
--     保险表(insurance)、基金表(fund)和投资资产表(property)，
--     列出所有客户的编号、名称和总资产，总资产命名为total_property。
--     总资产为储蓄卡余额，投资总额，投资总收益的和，再扣除信用卡透支的金额
--     (信用卡余额即为透支金额)。客户总资产包括被冻结的资产。
--    请用一条SQL语句实现该查询：

-- output list
SELECT c_id, c_name, IFNULL(bank_balance,0.0)+IFNULL(property_balance,0.0) AS total_property
FROM client

-- get bank balance; 储蓄卡is balance，信用卡is liability; so need to minus liability
LEFT JOIN (SELECT b_c_id, sum(if(b_type='储蓄卡',b_balance,0.0-b_balance))AS bank_balance
FROM bank_card
GROUP BY b_c_id)bank_table ON c_id=b_c_id

-- get property balance; property balance=property_amount++
-- property_amount=property quantity*(finance property amount + insurance amount + fund amount +property income)
-- first sub table to get property_amount++
LEFT JOIN (SELECT pro_c_id, sum(property_amount) AS property_balance
-- second sub table to get each property amount
FROM(SELECT DISTINCT pro_id, pro_c_id, pro_quantity*if(pro_type=1, p_amount, if(pro_type=2, i_amount, f_amount))+pro_income AS property_amount
-- from those table to get each amount where pro_type and pro_pif_id=each_id is true
FROM property, fund, insurance, finances_product
WHERE IF(pro_type=1, pro_pif_id=p_id, true)
AND IF(pro_type=2, pro_pif_id=i_id, true)
AND IF(pro_type=3, pro_pif_id=f_id, true))property_type_table
GROUP BY pro_c_id) property_table ON c_id=pro_c_id;


/*  end  of  your code  */ 