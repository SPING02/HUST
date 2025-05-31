-- 9) 查询购买了货币型(f_type='货币型')基金的用户的名称、电话号、邮箱。
--   请用一条SQL语句实现该查询：
-- output lisr
SELECT c_name, c_phone, c_mail
FROM client
WHERE c_id in
-- first sub table from table property to get fund type property
(SELECT pro_c_id FROM property WHERE pro_type=3 AND pro_pif_id IN
    -- second sub table from table fund to get coin type f_type
    (SELECT f_id FROM fund WHERE f_type='货币型')
)
ORDER BY c_id






/*  end  of  your code  */