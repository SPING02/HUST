use finance1;
drop trigger if exists before_property_inserted;
-- 请在适当的地方补充代码，完成任务要求：
delimiter $$
CREATE TRIGGER before_property_inserted BEFORE INSERT ON property 
FOR EACH ROW 
BEGIN
    DECLARE new_pro_type int default new.pro_type;
    DECLARE id int default new.pro_pif_id;
    DECLARE msg varchar(50);

    IF new_pro_type = 1 
    THEN
        IF id NOT IN(SELECT p_id FROM finances_product)
        THEN SET msg=concat("finances product #", id, " not found!");
        END IF;
    ELSEIF new_pro_type = 2
    THEN 
        IF id NOT IN(SELECT i_id FROM insurance)
        THEN SET msg=concat("insurance #", id, " not found!");
        END IF;
    ELSEIF new_pro_type = 3
    THEN 
        IF id NOT IN(SELECT f_id FROM fund)
        THEN SET msg=concat("fund #", id, " not found!");
        END IF;
    ELSE
        SET msg = concat("type ", new_pro_type, " is illegal!");
    END IF;
    
    IF msg IS NOT NULL
    THEN SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = msg;
    END IF;



END$$
 
delimiter ;

















