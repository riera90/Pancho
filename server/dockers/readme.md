you must copy all Dockerfile and docker-compose.yaml into the root or the project.  
For example, if you want to start the develop docker, you must, do as follows
        
        cp ./docker/dev/* ./
        docker-compose up --build
        
You might need to run ```docker-compose``` as root


Then, you will need to create the database

for dev:

	docker-compose exec web bin/console d:s:c


for postgress (prod and staging)

	docker-compose exec web bin/console d:d:c
	docker-compose exec web bin/console d:s:c


and you are good to go!
