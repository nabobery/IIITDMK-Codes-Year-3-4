from tensorflow.keras import layers, models
from tensorflow.keras.optimizers.legacy import Adam

def identity_block(x, filters, kernel_size=3, stride=1):
    x_skip = x

    x = layers.Conv2D(filters, kernel_size=1, strides=stride, padding='same')(x)
    x = layers.BatchNormalization()(x)
    x = layers.Activation('relu')(x)

    x = layers.Conv2D(filters, kernel_size, strides=1, padding='same')(x)
    x = layers.BatchNormalization()(x)
    x = layers.Activation('relu')(x)

    x = layers.Conv2D(filters*4, kernel_size=1, strides=stride, padding='same')(x)
    x = layers.BatchNormalization()(x)

    x = layers.add([x, x_skip])
    x = layers.Activation('relu')(x)
    return x

def convolutional_block(x, filters, kernel_size=3, stride=1):
    x_skip = x

    x = layers.Conv2D(filters, kernel_size=1, strides=stride, padding='same')(x)
    x = layers.BatchNormalization()(x)
    x = layers.Activation('relu')(x)

    x = layers.Conv2D(filters, kernel_size, strides=stride, padding='same')(x)
    x = layers.BatchNormalization()(x)
    x = layers.Activation('relu')(x)

    x = layers.Conv2D(filters*4, kernel_size=1, strides=stride, padding='same')(x)
    x = layers.BatchNormalization()(x)

    x_skip = layers.Conv2D(filters*4, kernel_size=1, strides=stride, padding='same')(x_skip)
    x_skip = layers.BatchNormalization()(x_skip)

    x = layers.add([x, x_skip])
    x = layers.Activation('relu')(x)
    return x

def dilated_convolutional_block(x, filters, kernel_size=3, stride=1):
    x_skip = x

    x = layers.Conv2D(filters, kernel_size=1, strides=stride, padding='same', dilation_rate=(3,3))(x)
    x = layers.BatchNormalization()(x)
    x = layers.Activation('relu')(x)

    x = layers.Conv2D(filters, kernel_size, strides=stride, padding='same', dilation_rate=(3,3))(x)
    x = layers.BatchNormalization()(x)
    x = layers.Activation('relu')(x)

    x = layers.Conv2D(filters*4, kernel_size=1, strides=stride, padding='same', dilation_rate=(3,3))(x)
    x = layers.BatchNormalization()(x)

    x_skip = layers.Conv2D(filters*4, kernel_size=1, strides=stride, padding='same')(x_skip)
    x_skip = layers.BatchNormalization()(x_skip)

    x = layers.add([x, x_skip])
    x = layers.Activation('relu')(x)
    return x

def ResNet152_With_Dilation(inputShape=(224,224,3),kernelSize=(3,3), num_classes=8):
    input_layer = layers.Input(shape=inputShape)

    x = layers.Conv2D(64, 7, strides=1, padding='same')(input_layer)
    x = layers.BatchNormalization()(x)
    x = layers.Activation('relu')(x)
    x = layers.MaxPooling2D(3, strides=2, padding='same')(x)

    x = convolutional_block(x, filters=64, kernel_size=3, stride=1)
    x = identity_block(x, filters=64, kernel_size=3)
    x = identity_block(x, filters=64, kernel_size=3)
    x = layers.MaxPooling2D(3, strides=2, padding='same')(x)

    x = convolutional_block(x, filters=128, kernel_size=3, stride=1)
    x = identity_block(x, filters=128, kernel_size=3)
    x = identity_block(x, filters=128, kernel_size=3)
    x = identity_block(x, filters=128, kernel_size=3)
    x = identity_block(x, filters=128, kernel_size=3)
    x = identity_block(x, filters=128, kernel_size=3)
    x = identity_block(x, filters=128, kernel_size=3)
    x = identity_block(x, filters=128, kernel_size=3)
    x = layers.MaxPooling2D(3, strides=2, padding='same')(x)

    x = convolutional_block(x, filters=256, kernel_size=3, stride=1)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = identity_block(x, filters=256, kernel_size=3)
    x = layers.MaxPooling2D(3, strides=2, padding='same')(x)

    x = dilated_convolutional_block(x, filters=512, kernel_size=3, stride=1)
    x = identity_block(x, filters=512, kernel_size=3)
    x = identity_block(x, filters=512, kernel_size=3)
    x = layers.MaxPooling2D(3, strides=2, padding='same')(x)

    x = layers.GlobalAveragePooling2D()(x)
    x = layers.Dense(num_classes, activation='softmax')(x)

    model = models.Model(inputs=input_layer, outputs=x, name='resnet152')
    return model

# resnet152 = ResNet152_With_Dilation(inputShape=(224, 224, 3), num_classes=8)

# resnet152.summary()