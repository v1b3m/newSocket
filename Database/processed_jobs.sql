-- Adminer 4.6.2 MySQL dump

SET NAMES utf8;
SET time_zone = '+00:00';
SET foreign_key_checks = 0;
SET sql_mode = 'NO_AUTO_VALUE_ON_ZERO';

DROP TABLE IF EXISTS `processed_jobs`;
CREATE TABLE `processed_jobs` (
  `job_id` int(6) unsigned zerofill NOT NULL AUTO_INCREMENT,
  `user_id` varchar(10) DEFAULT NULL,
  `type_of_task` varchar(10) NOT NULL,
  `processing_duration` double NOT NULL,
  `time_and_date` datetime NOT NULL,
  PRIMARY KEY (`job_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

INSERT INTO `processed_jobs` (`job_id`, `user_id`, `type_of_task`, `processing_duration`, `time_and_date`) VALUES
(000767,	'408326487',	'rev',	0.000007,	'2018-07-13 09:28:10'),
(000768,	'137512622',	'rev',	0.000003,	'2018-07-13 09:31:14'),
(000769,	'1545543631',	'dbl',	0.000005,	'2018-07-13 09:31:21'),
(000770,	'665602087',	'del',	0.000014,	'2018-07-13 09:31:27'),
(000771,	'1312043568',	'encrypt',	0.000037,	'2018-07-13 09:31:44'),
(000772,	'282384209',	'encrypt',	0.000027,	'2018-07-13 09:31:56'),
(000773,	'683273125',	'decrypt',	0.000224,	'2018-07-13 09:32:30'),
(000774,	'712065544',	'encrypt',	0.000036,	'2018-07-13 09:32:51'),
(000775,	'882155557',	'decrypt',	0.000296,	'2018-07-13 09:32:58'),
(000776,	'112746698',	'del',	0.000015,	'2018-07-13 09:33:53');

-- 2018-07-18 18:33:32
