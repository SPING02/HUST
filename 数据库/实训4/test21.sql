  -- 2) 投资积极且偏好理财类产品的客户
--   请用一条SQL语句实现该查询：
SELECT table1.pro_c_id
FROM (
  (SELECT pro_c_id, COUNT(DISTINCT(pro_pif_id))AS cnt1
  FROM property, finances_product
  WHERE pro_pif_id = p_id AND pro_type=1
  GROUP BY pro_c_id)
  AS table1
  JOIN
  (SELECT pro_c_id, COUNT(DISTINCT(pro_pif_id))AS cnt2
  FROM property, fund
  WHERE pro_pif_id = f_id AND pro_type=3
  GROUP BY pro_c_id)
  AS table2
  ON table1.pro_c_id = table2.pro_c_id
)
WHERE table1.cnt1 > table2.cnt2

/*  end  of  your code  */