<?php

namespace App\Repository;

use App\Entity\Configuration;
use Doctrine\Bundle\DoctrineBundle\Repository\ServiceEntityRepository;
use Symfony\Bridge\Doctrine\RegistryInterface;

/**
 * @method Configuration|null find($id, $lockMode = null, $lockVersion = null)
 * @method Configuration|null findOneBy(array $criteria, array $orderBy = null)
 * @method Configuration[]    findAll()
 * @method Configuration[]    findBy(array $criteria, array $orderBy = null, $limit = null, $offset = null)
 */
class ConfigurationRepository extends ServiceEntityRepository
{
    public function __construct(RegistryInterface $registry)
    {
        parent::__construct($registry, Configuration::class);
    }

    /**
     * @return Configuration
     * @throws \Exception
     *
     * returns the current configuration
     * if multiples configurations are found, the bigger index configuration is returned (the last configuration created)
     */
    public function getConfiguration(): Configuration
    {
        $querry = $this->createQueryBuilder('configuration')
            ->orderBy('configuration.id', 'DESC')
            ->getQuery()
            ->getResult()
        ;

        if (sizeof($querry) <= 0 ){
            Throw new \Exception('No configuration found, please, create a configuration in the server');
        }

        return $querry[0];
    }
}
