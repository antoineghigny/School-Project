# Members :
Cotton Ian 55019 | Ghigny Antoine 56359

## How to build & run the project

__Step 1__ : Create a certificate in XAMPP.
- Go to Xampp\apache and execute the makecert.bat and follow the steps.
  ![alt text](https://media.discordapp.net/attachments/941668041723379763/980210171680804894/unknown.png?width=720&height=503)

__Step 2__ : Put the project in Xampp\htdocs

__Step 3__ : Go to Xampp\htdocs\secg4-exam-computer-project\laravel-chat\
then open a shell and execute those commands

1. npm i
2. composer i
3. php artisan passport:install

__Step 4__ : Open two shell in Xampp\htdocs\secg4-exam-computer-project\laravel-chat\public

1. In the second execute : npm run watch

__Step 5__: In Xampp\htdocs\secg4-exam-computer-project\laravel-chat\ modify .env by insering those lines : 
```
PUSHER_APP_ID=1406413
PUSHER_APP_KEY=de62a5709f6c3254d175
PUSHER_APP_SECRET=ec3c7afd1f21fae68471
PUSHER_APP_CLUSTER=eu
```

__Step 6__: Create the database in Xampp\htdocs\secg4-exam-computer-project\laravel-chat\database with this command in a shell 
```
touch db.sqlite 
```

__Step 7__: Open a shell in Xampp\htdocs\secg4-exam-computer-project\laravel-chat and execute this command: 
```
 php artisan migrate
```

__Step 8__: modify the file .env-example change those line 

```
BROADCAST_DRIVER=log -> BROADCAST_DRIVER=pusher
DB_CONNECTION=mysql -> DB_CONNECTION=sqlite
```

You must also remove thoses lines : 
![alt text](https://cdn.discordapp.com/attachments/941668041723379763/980514263271604275/unknown.png)

__Step 9__: then execute this command
```
php artisan key:generate
```

__Step 10__ : Lauch apache and mySQL on Xampp. You can now access to the chat. The link is : https://localhost/secg4-exam-computer-project/laravel-chat/public

- If there is an internal server error, it could be this line to remove from public/.htaccess
````
RewriteRule ^(.*)$ public/$1 [L]
````

## Answer to the questions

The answers are in the PDF file. 
