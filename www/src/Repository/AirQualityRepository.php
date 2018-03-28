<?php

namespace App\Repository;

use App\Entity\AirQuality;
use Doctrine\Bundle\DoctrineBundle\Repository\ServiceEntityRepository;
use Doctrine\ORM\EntityRepository;
use Symfony\Bridge\Doctrine\RegistryInterface;

class AirQualityRepository extends ServiceEntityRepository
{
    public function __construct(RegistryInterface $registry)
    {
        parent::__construct($registry, AirQuality::class);
    }

    public function findOnlyQuality()
    {
        return $this->createQueryBuilder('aq')->select('aq.quality', 'aq.date')
            ->orderBy('aq.date', 'ASC')
            ->getQuery()
            ->getScalarResult();
    }
}