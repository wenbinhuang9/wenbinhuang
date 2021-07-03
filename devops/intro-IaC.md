# Introduction to Infrastructure as Code 

The idea of Iac comes with the cloud development. The basical idea behind cloud is based on virtualization techs.  

## What is IaC

We can manage infrastructure by just coding. 

From one way, it allows to define infrastructure by just using configuration.

I will use AWS cloudformation to define a EC2 infrastructure. 

```yml
Resources:
    MyInstance:
        Type: AWS::EC2::Instance
        Properties:
            AvailabilityZone: us-east-1a
            ImageId: ami-a4cd7fsdf
            InstanceType: t2.micro
```

The above configuration defines the infrastructure of an EC2 instance. So we are able to create infrustructure by just using configuration. 


But an EC2 instance is not enough, we want to have a public IP to make EC2 instance accessable. So we can use AWS elastic IP. 

```yml
Resources:
    MyInstance:
        Type: AWS::EC2::Instance
        Properties:
            AvailabilityZone: us-east-1a
            ImageId: ami-a4cd7fsdf
            InstanceType: t2.micro

    MyEIP:
        Type:AWS::EC2::EIP
        Properties:
            InstanceId: !Ref MyInstance
```

The above code creates an elastci IP and then associate with my EC2 instance. 

Usually, we want to access EC2 instance by ssh, so in this situation, we need to add a ssh security group. The following configuration is to add ssh security group 

```yml
Resources:
    MyInstance:
        Type: AWS::EC2::Instance
        Properties:
            AvailabilityZone: us-east-1a
            ImageId: ami-a4cd7fsdf
            InstanceType: t2.micro

    MyEIP:
        Type:AWS::EC2::EIP
        Properties:
            InstanceId: !Ref MyInstance
    SSHSecurityGroup:
        Type: AWS::EC2::SecurityGroup
        Properties:
            GroupDescription: Enable SSH access via port 22
            SecurityGroupIngress:
            - CidrIp: 0.0.0.0/0
              FromPort: 22
              IpProtocol: tcp
              ToPort: 22
```

In summary, compared with old times, we will configure infrastructure by manual operations directly on hardwares, which is errorous. However, with IaC tech, it is very easy to manage infrastructure just by coding. 
## Why Iac

1. Manual operations on hardwares are  prone to error and also time-consuming. 
2. IaC enables auto-scaling. 
3. Iac integrates with Devops to make infrastructure change more fast , reliable and trackable. 


## Reference 

[AWS CloudFormation Template Tutorial](https://www.youtube.com/watch?v=_jqwVpO1w6A)