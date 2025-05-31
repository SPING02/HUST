-- 5) 查询任意两个客户的相同理财产品数
--   请用一条SQL语句实现该查询：

-- output list
SELECT pro1.pro_c_id, pro2.pro_c_id, COUNT(*) AS total_count
FROM property AS pro1 INNER JOIN property AS pro2 ON pro1.pro_pif_id = pro2.pro_pif_id
-- same finances property but different pro_c_id
WHERE pro1.pro_type=1 AND pro2.pro_type =1 AND pro1.pro_c_id != pro2.pro_c_id
GROUP BY pro1.pro_c_id, pro2.pro_c_id
--  at least two same finances property
HAVING COUNT(*) >=2
ORDER BY pro1.pro_c_id;





/*  end  of  your code  */