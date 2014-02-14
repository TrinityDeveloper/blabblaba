-- Fix priest spirit of redemption
DELETE FROM `spell_script_names` WHERE `spell_id`=27827;
INSERT INTO `spell_script_names` VALUES
('27827', 'priest_spirit_of_redemption');
-- Fix Shadowfiend
DELETE FROM `spell_proc_event` WHERE  `entry`=28305;
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES
(28305, 32, 0, 0, 0, 0, 0, 4, 0, 100, 0);
-- Warlock Seduction
DELETE FROM `spell_script_names` WHERE `spell_id`=6358;
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(6358,'spell_warl_seduction');
-- Prayer of mending
DELETE FROM `spell_proc_event` WHERE  `entry`=14892;
DELETE FROM `spell_proc_event` WHERE  `entry`=15362;
DELETE FROM `spell_proc_event` WHERE  `entry`=15363;
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES
(14892, 0, 6, 268443136, 65572, 0, 0, 87376, 0, 100, 0),
(15362, 0, 6, 268443136, 65572, 0, 0, 87376, 0, 100, 0),
(15363, 0, 6, 268443136, 65572, 0, 0, 87376, 0, 100, 0);
-- Trauma
DELETE FROM `spell_proc_event` WHERE  `entry`=71865;
DELETE FROM `spell_proc_event` WHERE  `entry`=71868;
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES 
(71865, 0, 0, 0, 0, 0, 278528, 0, 0, 1, 0),
(71868, 0, 0, 0, 0, 0, 278528, 0, 0, 1, 0);
--creature_template_outfits
CREATE TABLE IF NOT EXISTS `creature_template_outfits` (
  `entry` INT(10) UNSIGNED NOT NULL,
  `race` tinyint(3) UNSIGNED NOT NULL DEFAULT '1',
  `gender` tinyint(3) UNSIGNED NOT NULL DEFAULT '0' COMMENT '0 for male, 1 for female',
  `skin` tinyint(3) UNSIGNED NOT NULL DEFAULT '0',
  `face` tinyint(3) UNSIGNED NOT NULL DEFAULT '0',
  `hair` tinyint(3) UNSIGNED NOT NULL DEFAULT '0',
  `haircolor` tinyint(3) UNSIGNED NOT NULL DEFAULT '0',
  `facialhair` tinyint(3) UNSIGNED NOT NULL DEFAULT '0',
  `head` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `shoulders` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `body` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `chest` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `waist` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `legs` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `feet` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `wrists` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `hands` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `back` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `tabard` INT(10) UNSIGNED NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
 
-- Data exporting was unselected.
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;