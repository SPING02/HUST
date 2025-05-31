-- 1) 查询销售总额前三的理财产品
--   请用一条SQL语句实现该查询：
SELECT * FROM(
    SELECT pyear, rank() over(partition by pyear ORDER BY sumamount DESC) as rk, p_id,sumamount
    FROM(
        SELECT year(pro_purchase_time) AS pyear, p_id, SUM(p_amount * pro_quantity) AS sumamount
        FROM property, finances_product
        WHERE pro_pif_id=p_id AND pro_type=1 AND year(pro_purchase_time) IN (2010,2011) 
        GROUP BY p_id, pyear
    )AS table1
)AS table2
WHERE rk<=3;







/*  end  of  your code  */