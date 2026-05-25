create database IF NOT EXISTS secad_minifacebook;
CREATE USER IF NOT EXISTS 'secad_team2_user'@'localhost' IDENTIFIED BY  'secad_team2_pw';
ALTER USER 'secad_team2_user'@'localhost' IDENTIFIED BY 'secad_team2_pw';
GRANT ALL ON secad_minifacebook.* TO 'secad_team2_user'@'localhost';
FLUSH PRIVILEGES;
USE secad_minifacebook;
drop table if exists users;
drop table if exists comments;
drop table if exists posts;
create table users(
  username varchar(50) PRIMARY KEY,
  password varchar(100) NOT NULL,
  role enum('user','admin') NOT NULL DEFAULT 'user');

create table posts(
  id int auto_increment primary key,
  username varchar(50) not null,
  body text not null,
  created_at timestamp not null default current_timestamp,
  updated_at timestamp not null default current_timestamp on update current_timestamp,
  constraint fk_posts_user foreign key (username) references users(username) on delete cascade
);

create table comments(
  id int auto_increment primary key,
  post_id int not null,
  username varchar(50) not null,
  body text not null,
  created_at timestamp not null default current_timestamp,
  constraint fk_comments_post foreign key (post_id) references posts(id) on delete cascade,
  constraint fk_comments_user foreign key (username) references users(username) on delete cascade
);

create index idx_posts_created_at on posts(created_at);
create index idx_comments_post_created on comments(post_id, created_at);
-- Seed accounts use email-style usernames to match the auth form validation.
-- All seeded users are admins so the RBAC path can be tested immediately.
INSERT INTO users(username,password,role) VALUES ('pruettt1@udayton.edu',md5('Tommy123'),'admin');
INSERT INTO users(username,password,role) VALUES ('mooreb26@udayton.edu',md5('Bennett123'),'admin');
INSERT INTO users(username,password,role) VALUES ('testaa2@udayton.edu',md5('Alex123'),'admin');
