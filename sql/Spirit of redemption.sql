-- Fix priest spirit of redemption
DELETE FROM `spell_script_names` WHERE `spell_id`=27827;
INSERT INTO `spell_script_names` VALUES
('27827', 'priest_spirit_of_redemption');