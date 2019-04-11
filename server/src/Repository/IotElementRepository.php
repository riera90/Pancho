<?php

namespace App\Repository;

use App\Entity\IotElement;
use Doctrine\Bundle\DoctrineBundle\Repository\ServiceEntityRepository;
use Symfony\Bridge\Doctrine\RegistryInterface;

/**
 * @method IotElement|null find($id, $lockMode = null, $lockVersion = null)
 * @method IotElement|null findOneBy(array $criteria, array $orderBy = null)
 * @method IotElement[]    findAll()
 * @method IotElement[]    findBy(array $criteria, array $orderBy = null, $limit = null, $offset = null)
 */
class IotElementRepository extends ServiceEntityRepository
{
    public function __construct(RegistryInterface $registry)
    {
        parent::__construct($registry, IotElement::class);
    }

    // /**
    //  * @return IotElement[] Returns an array of IotElement objects
    //  */
    /*
    public function findByExampleField($value)
    {
        return $this->createQueryBuilder('i')
            ->andWhere('i.exampleField = :val')
            ->setParameter('val', $value)
            ->orderBy('i.id', 'ASC')
            ->setMaxResults(10)
            ->getQuery()
            ->getResult()
        ;
    }
    */

    /*
    public function findOneBySomeField($value): ?IotElement
    {
        return $this->createQueryBuilder('i')
            ->andWhere('i.exampleField = :val')
            ->setParameter('val', $value)
            ->getQuery()
            ->getOneOrNullResult()
        ;
    }
    */
}
