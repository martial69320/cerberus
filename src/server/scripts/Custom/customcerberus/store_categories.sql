DROP TABLE IF EXISTS `store_categories`;

CREATE TABLE `store_categories` (
  `cat_id` int(11) NOT NULL,
  `name` varchar(100) NOT NULL,
  PRIMARY KEY (`cat_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
